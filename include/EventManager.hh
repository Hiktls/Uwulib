#ifndef EVENT_HH
#define EVENT_HH

#include <SDL2/SDL.h>
class EventManager {
    private:
        int alive = 1;
    public:
        void Queue(struct queueRun);
};

#endif