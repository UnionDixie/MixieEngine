#pragma once

class Input
{
public:
    static Input& getInstance() // Singleton is accessed via getInstance()
    {
        static Input instance; // lazy singleton, instantiated on first use
        return instance;
    }

    static void mouseButtonCallback(int key, int action) // this method is specified as glfw callback
    {
        //here we access the instance via the singleton pattern and forward the callback to the instance method
        getInstance().mouseButtonCallbackImpl(key, action);
    }

    void mouseButtonCallbackImpl(int key, int action) //this is the actual implementation of the callback method
    {
        //the callback is handled in this instance method           
        //... [CODE here]
    }


private:
    Input(void) // private constructor necessary to allow only 1 instance
    {
    }

    Input(Input const&); // prevent copies
    void operator=(Input const&); // prevent assignments
};