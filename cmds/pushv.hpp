#ifndef PSV_HPP
#define PSV_HPP

#include "../rte/objs/command.hpp"
#include "../rte/runtime.hpp"
#include "../rte/registers.hpp"
#include "../rte/compiler.hpp"
#include "../rte/variables.hpp"
#include "../rte/lists.hpp"

class Pushv : public Command
{
private:
    std::regex name = std::regex("^((P|p)(U|u)(S|s)(H|h)(V|v))");
    std::regex r_regs = std::regex("(ax|bx|cx|dx|ex|fx|gx|hx)");

    std::regex r_int = std::regex("[0-9]*");
    std::smatch match;
public:
    void runFunction(std::vector<std::string> args)
    {
        std::string var = args[0];

        if (Variables.existsVariable(var) || Variables.existsRealVariable(var))
        {
            Compiler.addLine("stack.push(*"+var+");");
            return;
        }
		else if (Lists.existsList(var))
		{
			Compiler.addLine("\n\tfor (int _int_sys_i_ = "+var+".size(); _int_sys_i_ >= 0; _int_sys_i_--)\n\t\tstack.push("+var+"[_int_sys_i_]);");
			return;
		}

        std::cout << "ERROR: LINE " << Runtime.LineNumber << ": VARIABLE_DOESNT_EXIST: \"" << var << "\"" << std::endl;
        exit(0);
    }

    std::regex getName()
    {
        return name;
    }
};

#endif
