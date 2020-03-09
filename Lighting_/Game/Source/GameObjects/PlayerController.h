#ifndef __PlayerController_H__
#define __PlayerController_H__

class Event;

class PlayerController
{
    enum Directions
    {
        DIR_UP      = 0x0001,
        DIR_DOWN    = 0x0002,
        DIR_LEFT    = 0x0004,
        DIR_RIGHT   = 0x0008,
        DIR_JUMP    = 0x0010,
        DIR_LIFT    = 0x0020,
        DIR_DROP    = 0x0040,
        DIR_ENTER   = 0x0080

    };

protected:
    int m_Directions;

public:
    void OnEvent(Event* pEvent);

    bool IsHeld_Up() { return m_Directions & DIR_UP; }
    bool IsHeld_Down() { return m_Directions & DIR_DOWN; }
    bool IsHeld_Left() { return m_Directions & DIR_LEFT; }
    bool IsHeld_Right() { return m_Directions & DIR_RIGHT; }
    bool IsHeld_Jump() { return m_Directions & DIR_JUMP; }
    bool IsHeld_Lift() { return m_Directions & DIR_LIFT; }
    bool IsHeld_Drop() { return m_Directions & DIR_DROP; }
    bool IsHeld_Enter() { return m_Directions & DIR_ENTER; }

};

#endif //__PlayerController_H__
