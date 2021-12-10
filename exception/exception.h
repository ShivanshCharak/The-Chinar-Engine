#pragma once

#include <string>
#include <sstream>

namespace Chinar {
    
    class Exception {
        public:
            template <typename... T>
            Exception(const std::string& functionName, T&&... args) {
                std::stringstream ss; 

                ss << "Error in " << functionName << "():\n";
                ((ss << std::forward<T>(args) << ' '), ...);

                mError = ss.str();
            }

            const std::string& what() const {
                return mError;
            }

        private:

            std::string mError;
    };

#define NEW_EXCEPTION(className) \
    class className : public Exception {      \
        public:                                                         \
            template <typename... T>                                    \
            className(const std::string& functionName, T&&... args)     \
            :   Exception(functionName, args...) {}                     \
    };

    NEW_EXCEPTION(EngineException);
    NEW_EXCEPTION(AIException);
}
