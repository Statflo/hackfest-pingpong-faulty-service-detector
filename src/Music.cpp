#include <Arduino.h>
#include "pins.cpp"                                                      
#include "Notes.h"  

class Music
{
    public:
        int counter;
        int marioDeath[35] = {17,                                                  // Array for Death sound effect & song
          NOTE_C4, 32, NOTE_CS4, 32, NOTE_D4, 16, NOTE_H, 4, NOTE_H, 2, NOTE_B3, 8, NOTE_F4, 8, NOTE_H, 8, NOTE_F4, 8, NOTE_F4, 6, 
          NOTE_E4, 6, NOTE_D4, 6, NOTE_C4, 8, NOTE_E3, 8, NOTE_H, 8, NOTE_E3, 8, NOTE_C3, 8};
        int marioOver[31] =  {15,                                               // Array for Game over song
          NOTE_C4, 8, NOTE_H, 8, NOTE_H, 8, NOTE_G3, 8, NOTE_H, 4, NOTE_E3, 4, NOTE_A3, 6, NOTE_B3, 6, NOTE_A3, 6, NOTE_GS3, 6, NOTE_AS3, 6, 
          NOTE_GS3, 6, NOTE_G3, 8, NOTE_F3, 8, NOTE_G3, 4};
    
        void playDeath()
        {
            for (int thisNote = 1; thisNote < (this->marioDeath[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
                tone(speakerID, this->marioDeath[thisNote], (1000/this->marioDeath[thisNote + 1]));      // Play the single note
                delay((1000/this->marioDeath[thisNote + 1]) * 1.30);                           // Delay for the specified time
                noTone(speakerID);                                                 // Silence the note that was playing
            }
        }
        
        void playOver()
        {
            for (int thisNote = 1; thisNote < (this->marioOver[0] * 2 + 1); thisNote = thisNote + 2) { // Run through the notes one at a time
                tone(speakerID, this->marioOver[thisNote], (1000/this->marioOver[thisNote + 1]));// Play the single note
                delay((1000/this->marioOver[thisNote + 1]) * 1.30);                        // Delay for the specified time
                noTone(speakerID);                                                 // Silence the note that was playing
            }
        }
        
        void playMusic()
        {
            if (this->counter == 0) {
                playDeath();
                this->counter = 1;
                return;
            }
            
            playOver();
            this->counter = 0;  
        }
};




