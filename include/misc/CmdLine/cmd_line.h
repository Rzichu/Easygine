#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <utility>

#define CMD_PARAMS  const std::vector<std::string> &

namespace aether {
    namespace cmdline {
        class ConsoleBase;
        struct Command;

        struct Command {
            Command(std::function<void(const std::vector<std::string> &)> func, unsigned int min_args, const std::string &desc, const std::string &detailinfo, bool hidden = false);

            Command()           = default;
            virtual ~Command()  = default;

            std::function<void(const std::vector<std::string> &)> func_ptr;
            unsigned int min_rq_args {0};
            std::string description {"No description available."};
            std::string details {""};
            bool is_hidden {false};
        };

        class ConsoleBase {
        public:
            enum class EC_Result {
                  Success
                , UnknownCmd
                , NotEnoughArgs
                , BadArgs
            };

        public:
            virtual bool addCmd(const std::string &cmd_name, const Command &cmd);
            
            virtual bool addCmd(const std::string &cmd_name, std::function<void(const std::vector<std::string> &)> func, unsigned int min_args = 0
                    , const std::string &desc = "No description available.", const std::string &detailinfo = "", bool hidden = false);
            
            virtual void removeCmd(const std::string &cmd_name);

            virtual EC_Result parse(std::string cmd_line);

        public:
            ConsoleBase()           = default;
            virtual ~ConsoleBase()  = default;

        protected:
            std::unordered_map<std::string, Command> m_Commands;
        };
    }
}