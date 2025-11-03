#include "cmd_line.h"

#include <stdexcept>

namespace aether::cmdline {
    Command::Command(std::function<void(const std::vector<std::string> &)> func, unsigned int min_args, const std::string &desc, const std::string &detailinfo, bool hidden)
        : func_ptr(func)
        , min_rq_args(min_args)
        , description(desc)
        , details(detailinfo)
        , is_hidden(hidden)
        {}

    bool ConsoleBase::addCmd(const std::string &cmd_name, const Command &cmd) {
        if (cmd.func_ptr != nullptr) {
            if (this->m_Commands.count(cmd_name)) {
                return false;
            }
            this->m_Commands.emplace(cmd_name, cmd);
            return true;
        }
        return false;
    }

    bool ConsoleBase::addCmd(const std::string &cmd_name, std::function<void(const std::vector<std::string> &)> func, unsigned int min_args, const std::string &desc, const std::string &detailinfo, bool hidden) {
        if (func != nullptr) {
            if (this->m_Commands.count(cmd_name)) {
                return false;
            }
            this->m_Commands.emplace(cmd_name, Command(func, min_args, desc, detailinfo, hidden));
            return true;
        }
        return false;
    }

    void ConsoleBase::removeCmd(const std::string &cmd_name) {
        if (this->m_Commands.count(cmd_name)) {
            this->m_Commands.erase(cmd_name);
        }
    }

    ConsoleBase::EC_Result ConsoleBase::parse(std::string cmd_line) {
        unsigned long long space_break {cmd_line.find(" ", 0)};
        std::string cmd_name {cmd_line.substr(0, space_break)};
        std::vector<std::string> cmd_args;
        
        if (this->m_Commands.count(cmd_name)) {
            while (space_break != cmd_line.npos) {
                cmd_line.erase(0, space_break + 1);
                space_break = cmd_line.find(" ", 0);
                cmd_args.emplace_back(cmd_line.substr(0, space_break));
            }
        }
        else {
            return ConsoleBase::EC_Result::UnknownCmd;
        }
        
        if (cmd_args.size() < static_cast<long long>(this->m_Commands.at(cmd_name).min_rq_args)) {
            return ConsoleBase::EC_Result::NotEnoughArgs;
        }

        try {
            this->m_Commands.at(cmd_name).func_ptr(cmd_args);
        }
        catch (...) {
            return ConsoleBase::EC_Result::BadArgs;
        }
        return ConsoleBase::EC_Result::Success;
    }
}