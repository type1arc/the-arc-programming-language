#include <iostream>
#include <string>
#include <stack>

enum NODE_TYPE { NODE_ADD, NODE_SUB, NODE_MUL, NODE_DIV, NODE_NUM };

struct AST_node 
{
  NODE_TYPE type; 
  int value;
  AST_node* left;
  AST_node* right;
  AST_node(NODE_TYPE _type, int val=0) : type(_type), value(val), left(nullptr), right(nullptr) {} 

  std::stack<std::string> reg_stack;
  int reg_counter = 0;

  std::string allocate_register() { return "R" + std::to_string(++reg_counter); }
  void emit(const std::string& instr) { std::cout << instr << std::endl; }

  // code generator using recursion
  void code_generator(AST_node* node)
  {
    if (!node) return;

    if (node->type == NODE_NUM)
    {
      std::string reg = allocate_register(); 
      emit("mov " + reg + ", " + std::to_string(node->value));
      reg_stack.push(reg);
      return;
    }

    code_generator(node->left);
    code_generator(node->right); 

    std::string right_reg = reg_stack.top(); reg_stack.pop();
    std::string left_reg = reg_stack.top(); reg_stack.pop(); 

      switch (node->type) 
      {
              case NODE_ADD:
                  emit("ADD " + left_reg + ", " + right_reg);
                  break;
              case NODE_SUB:
                  emit("SUB " + left_reg + ", " + right_reg);
                  break;
              case NODE_MUL:
                  emit("MUL " + left_reg + ", " + right_reg);
                  break;
              case NODE_DIV:
                  emit("DIV " + left_reg + ", " + right_reg);
                  break;
              default:
                  throw std::runtime_error("Unknown node type in code generator");
      }
      // push target register holding the result back
      reg_stack.push(left_reg);
    }
};
