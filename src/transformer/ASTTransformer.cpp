#include "transformer/ASTTransformer.hpp" 
#include "AST/nodes/Program.hpp"
#include "AST/nodes/Statement.hpp"
#include "AST/nodes/Identifier.hpp"
#include "AST/nodes/Expression.hpp"
#include "AST/nodes/FloatFactor.hpp"
#include "AST/nodes/IntegerFactor.hpp"
#include "AST/nodes/StringFactor.hpp"
#include "AST/nodes/Operation.hpp"
#include "AST/nodes/PrintStatement.hpp"
#include "AST/nodes/ExitStatement.hpp"
#include "AST/nodes/Assignement.hpp"
#include <stdexcept>

namespace YANKI {
void ASTTransformer::visitProgram(Program* program) {
    
    llvm::FunctionType* mainType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(context),  // Return type
        false                             // No parameters
    );
    
    currentFunction = llvm::Function::Create(
        mainType,
        llvm::Function::ExternalLinkage,
        "main",
        module
    );

    // Create entry basic block
    llvm::BasicBlock* entryBB = llvm::BasicBlock::Create(context, "entry", currentFunction);
    builder.SetInsertPoint(entryBB);

    for (auto* statement : program->getChildren()) {
        statement->accept(this);
    }


    // If no explicit return, add one
    if (!builder.GetInsertBlock()->getTerminator()) {
        builder.CreateRet(llvm::ConstantInt::get(context, llvm::APInt(32, 0)));
    }

}

void ASTTransformer::visitFloatFactor(FloatFactor* floatFactor) {
    llvm::Value* floatVal = llvm::ConstantFP::get(context, llvm::APFloat(floatFactor->getValue()));
    namedValues["lastValue"] = floatVal;
}

void ASTTransformer::visitIntegerFactor(IntegerFactor* integerFactor) {
    llvm::Value* intVal = llvm::ConstantInt::get(context, llvm::APInt(32, integerFactor->getValue()));
    namedValues["lastValue"] = intVal;
}

void ASTTransformer::visitStringFactor(StringFactor* stringFactor) {
    llvm::Value* strVal = builder.CreateGlobalStringPtr(stringFactor->getValue(), "str_const");
    namedValues["lastValue"] = strVal;
}

void ASTTransformer::visitOperation(Operation* operation) {

    // Create a new basic block for the operation
    llvm::BasicBlock* opBB = llvm::BasicBlock::Create(
        context, 
        "operation",
        currentFunction,
        builder.GetInsertBlock()->getNextNode()
    );
    builder.CreateBr(opBB);
    builder.SetInsertPoint(opBB);

    operation->getFactor1()->accept(this);
    llvm::Value* lhs = namedValues["lastValue"];

    operation->getFactor2()->accept(this);
    llvm::Value* rhs = namedValues["lastValue"];

    llvm::Value* result = nullptr;
    switch (operation->getOp()) {
        case OpType::ADD:
            result = builder.CreateAdd(lhs, rhs, "addtmp");
            break;
        case OpType::SUB:
            result = builder.CreateSub(lhs, rhs, "subtmp");
            break;
        case OpType::MUL:
            result = builder.CreateMul(lhs, rhs, "multmp");
            break;
        case OpType::DIV:
            result = builder.CreateUDiv(lhs, rhs, "divtmp");
            break;
        default:
            throw std::runtime_error("Unsupported operation");
    }
    namedValues["lastValue"] = result;
}

void ASTTransformer::visitPrintStatement(PrintStatement* printStatement) {
    // Visit the expression to compute its value
    printStatement->getExpression()->accept(this);
    llvm::Value* value = namedValues["lastValue"];

    // Get the printf function
    llvm::FunctionCallee printfFunc = module.getOrInsertFunction(
        "printf",
        llvm::FunctionType::get(
            llvm::IntegerType::getInt32Ty(context),
            llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0),
            true // printf is a variadic function
        )
    );

    // Create the format string based on the type of the value
    llvm::Value* formatStr = nullptr;
    if (value->getType()->isFloatingPointTy()) {
        formatStr = builder.CreateGlobalStringPtr("%f\n", "floatFormat");
    } else if (value->getType()->isIntegerTy()) {
        formatStr = builder.CreateGlobalStringPtr("%d\n", "intFormat");
    } else {
        // Handle other types or throw an error
        throw std::runtime_error("Unsupported type for print statement");
    }

    // Prepare the arguments for printf
    std::vector<llvm::Value*> args;
    args.push_back(formatStr); // First argument: format string
    args.push_back(value);     // Second argument: value to print

    // Emit the call to printf
    builder.CreateCall(printfFunc, args, "printfCall");
}

void ASTTransformer::visitExitStatement(ExitStatement* exitStatement) {
    llvm::Value* exitCode = llvm::ConstantInt::get(context, llvm::APInt(32, exitStatement->getExitCode()));
    builder.CreateRet(exitCode);
}

void ASTTransformer::visitAssignement(Assignement* assignement) {
    llvm::BasicBlock* assignBB = llvm::BasicBlock::Create(
        context,
        "assign",
        currentFunction,
        builder.GetInsertBlock()->getNextNode()
    );
    builder.CreateBr(assignBB);
    builder.SetInsertPoint(assignBB);

    assignement->getExpression()->accept(this);
    llvm::Value* exprValue = namedValues["lastValue"];
    std::string identifier = ((Identifier*)assignement->getIdentifier())->getVarName();
    llvm::AllocaInst* variable = (llvm::AllocaInst*)namedValues[identifier];
    if (!variable) {
        variable = builder.CreateAlloca(exprValue->getType(), nullptr, identifier);
        namedValues[identifier] = variable;
    }
    builder.CreateStore(exprValue, variable);
}

void ASTTransformer::visitIdentifier(Identifier* identifier) {
    llvm::Value* value = namedValues[identifier->getVarName()];
    if (!value) {
        throw std::runtime_error("Undefined variable: " + identifier->getVarName());
    }
    namedValues["lastValue"] = builder.CreateLoad(llvm::Type::getInt32Ty(context), value, identifier->getVarName());
}

void ASTTransformer::visitStatement(Statement* statement) {
    for (Visitable* child : statement->getChildren()) {
        child->accept(this);
    }
}

void ASTTransformer::showIR()const{
  module.print(llvm::errs(), nullptr);
}

}  // namespace YANKI
