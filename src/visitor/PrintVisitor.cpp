#include "visitor/PrintVisitor.hpp"
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
#include "Constants.hpp"
#include <iomanip>

namespace YANKI {

void PrintVisitor::printIndent() {
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << indentStr;
    }
}

std::string PrintVisitor::getOperationSymbol(OpType op) {
    switch (op) {
        case OpType::ADD: return "+";
        case OpType::SUB: return "-";
        case OpType::MUL: return "*";
        case OpType::DIV: return "/";
        default: return "?";
    }
}

void PrintVisitor::visitProgram(Program* program) {
    std::cout << BOLD << BLUE << "Program" << RESET << " {\n";
    indentLevel++;
    for (Visitable* statement : program->getChildren()) {
        printIndent();
        statement->accept(this);
    }
    indentLevel--;
    printIndent();
    std::cout << "}\n";
}

void PrintVisitor::visitFloatFactor(FloatFactor* floatFactor) {
    std::cout << CYAN << "Float" << RESET << "(" 
              << YELLOW << std::fixed << std::setprecision(4) 
              << floatFactor->getValue() << RESET << ")\n";
}

void PrintVisitor::visitIdentifier(Identifier* identifier) {
    std::cout << MAGENTA << "Identifier" << RESET << "(" 
              << GREEN << identifier->getVarName() << RESET << ")\n";
}

void PrintVisitor::visitIntegerFactor(IntegerFactor* integerFactor) {
    std::cout << CYAN << "Integer" << RESET << "(" 
              << YELLOW << integerFactor->getValue() << RESET << ")\n";
}

void PrintVisitor::visitStringFactor(StringFactor* stringFactor) {
    std::cout << CYAN << "String" << RESET << "(" 
              << GREEN << "\"" << stringFactor->getValue() << "\"" << RESET << ")\n";
}

void PrintVisitor::visitOperation(Operation* operation) {
    std::cout << MAGENTA << "Operation" << RESET << "(" 
              << RED << getOperationSymbol(operation->getOp()) << RESET << ") {\n";
    indentLevel++;
    printIndent();
    std::cout << "Left: ";
    operation->getFactor1()->accept(this);
    printIndent();
    std::cout << "Right: ";
    operation->getFactor2()->accept(this);
    indentLevel--;
    printIndent();
    std::cout << "}\n";
}

void PrintVisitor::visitStatement(Statement* statement) {
    std::cout << BLUE << "Statement" << RESET << " {\n";
    indentLevel++;
    for (Visitable* expression : statement->getChildren()) {
        printIndent();
        expression->accept(this);
    }
    indentLevel--;
    printIndent();
    std::cout << "}\n";
}

void PrintVisitor::visitPrintStatement(PrintStatement* printStatement) {
    std::cout << BLUE << "Print" << RESET << " {\n";
    indentLevel++;
    printIndent();
    printStatement->getExpression()->accept(this);
    indentLevel--;
    printIndent();
    std::cout << "}\n";
}

void PrintVisitor::visitExitStatement(ExitStatement* exitStatement) {
    std::cout << RED << "Exit" << RESET << "(" 
              << YELLOW << exitStatement->getExitCode() << RESET << ")\n";
}

void PrintVisitor::visitAssignement(Assignement* assignement) {
    std::cout << BLUE << "Assignment" << RESET << " {\n";
    indentLevel++;
    printIndent();
    std::cout << "Variable: ";
    assignement->getIdentifier()->accept(this);
    printIndent();
    std::cout << "Value: ";
    assignement->getExpression()->accept(this);
    indentLevel--;
    printIndent();
    std::cout << "}\n";
}

}  // namespace YANKI