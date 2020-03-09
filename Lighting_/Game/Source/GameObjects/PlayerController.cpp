#include "GamePCH.h"

#include "GameObjects/PlayerController.h"

void PlayerController::OnEvent(Event* pEvent)
{
    if( pEvent->GetEventType() == EventType_Input )
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>( pEvent );

        if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard )
        {
            int keyID = pInput->GetID();

            if( pInput->GetInputState() == InputState_Pressed )
            {
                if(keyID == 'W' ) { m_Directions |= DIR_UP; }
                if(keyID == 'S' ) { m_Directions |= DIR_DOWN; }
                if(keyID == 'A' ) { m_Directions |= DIR_LEFT; }
                if(keyID == 'D' ) { m_Directions |= DIR_RIGHT; }
                if( keyID == 'Z'      || keyID == ' ' ) { m_Directions |= DIR_JUMP; }
                if (keyID == VK_UP) { m_Directions |= DIR_LIFT; }
                if (keyID == VK_DOWN) { m_Directions |= DIR_DROP; }
                if (keyID == VK_RETURN) { m_Directions |= DIR_ENTER; }

            }

            if( pInput->GetInputState() == InputState_Released )
            {
                if(keyID == 'W' ) { m_Directions &= ~DIR_UP; }
                if(keyID == 'S' ) { m_Directions &= ~DIR_DOWN; }
                if(keyID == 'A' ) { m_Directions &= ~DIR_LEFT; }
                if(keyID == 'D' ) { m_Directions &= ~DIR_RIGHT; }
                if( keyID == 'Z'      || keyID == ' ' ) { m_Directions &= ~DIR_JUMP; }
                if (keyID == VK_UP) { m_Directions &= ~DIR_LIFT; }
                if (keyID == VK_DOWN) { m_Directions &= ~DIR_DROP; }
                if (keyID == VK_RETURN) { m_Directions &= ~DIR_ENTER; }
            }
        }
#endif
    }
}
