#pragma once

namespace eng
{
    class Application
    {
    public:
        virtual bool Init() = 0;
        virtual void Update(float deltaTime) = 0; // deltaTime in seconds
        virtual void Destroy() = 0;

        void SetNeedsToBeClose(bool value);
        bool NeedsToBeClosed() const;

    private:
        bool m_needsToBeClosed = false;

    };
}