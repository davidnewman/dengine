#ifndef _DENGINE_COMMON_INCL
#define _DENGINE_COMMON_INCL

#include <exception>
#include <SDL.h>
#include <SDL_image.h>

namespace dengine {
    class SdlException : public std::exception {
        public:
            SdlException(int code) 
               : msg{SDL_GetError()}, errorCode{code} {} 

            SdlException() : SdlException(0) {};

            const char* what() const throw() { return msg; }
            int code() const { return errorCode; }

        private:
            const char* msg;
            int errorCode;
    };

    class SDL {
        public:
            SDL(unsigned int flags);
    };
}
#endif
