/*
 * PlayRtttl.h
 *
 * Includes 21 sample melodies.
 * The example melodies may have copyrights you have to respect.
 * More RTTTL songs can be found under http://www.picaxe.com/RTTTL-Ringtones-for-Tune-Command/
 *
 *  Copyright (C) 2018  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *     Based on the RTTTL.pde example code written by Brett Hagman
 *     http://www.roguerobotics.com/
 *     bhagman@roguerobotics.com
 *
 *
 *  This file is part of PlayRttl https://github.com/ArminJo/PlayRttl.
 *
 *  PlayRttl is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#ifndef SRC_PLAYRTTTL_H_
#define SRC_PLAYRTTTL_H_

#if defined(__SAM3X8E__)
#error "Sorry no tone library for Arduino Due"
#endif
#if defined(__AVR__)
#include <avr/pgmspace.h>
#endif
#include "pitches.h"

#define VERSION_PLAY_RTTTL "1.4.0"
#define VERSION_PLAY_RTTTL_MAJOR 1
#define VERSION_PLAY_RTTTL_MINOR 4

/*
 * Version 1.4.0 - 1/2020
 * - Supporting direct tone output at pin 11 for ATmega328. Can be used with interrupt blocking libraries for NeoPixel etc.
 * - Use Print * instead of Stream *.
 * - Improved non-AVR compatibility.
 * - New Christmas songs example.
 *
 * Version 1.3.0 - 10/2019
 * - Support all octaves below 8.
 * - New styles '1' to '9' in addition to RTX styles 'C', 'N', 'S'.
 *
 * Version 1.2.2 - 6/2019
 * - Porting to non AVR architectures.
 *
 * Version 1.2.1 - 5/2019
 * - Natural is the new default style.
 * - New RTTTLMelodiesSmall sample array with less entries.
 * - Parameter now order independent.
 * - Modified oneMelody example.
 *
 * Version 1.2.0 - 5/2019
 * - No Serial.print statements in this library anymore, to avoid problems with different Serial implementations.
 * - Function playRandomRtttlBlocking() + startPlayRandomRtttlFromArrayPGM() do not print name now. If needed, use new functions playRandomRtttlSampleBlockingAndPrintName() + startPlayRandomRtttlFromArrayPGMAndPrintName().
 * - Printing functions have parameter (..., Print * aSerial) to print to any serial. Call it (..., &Serial) to use standard Serial;
 * - playRandomRtttlBlocking() renamed to playRandomRtttlSampleBlocking() and bug fixing.
 *
 * Version 1.1 - 5/2019
 * - new setNumberOfLoops() and setDefaultStyle() functions.
 */

//#define USE_NON_STANDARD_SERIAL_FOR_DEBUG // if activated you must -you are able to- set your own serial class for debugging purposes by setSerialForPlayRtttlDebug()

#if ! defined(USE_NO_RTX_EXTENSIONS) // if defined it suppresses the next 2 defines / useful for ATtinies to shrink code
#define SUPPORT_RTX_EXTENSIONS  // needs additional 200 bytes FLASH - support loop and style
#define SUPPORT_RTX_FORMAT      // needs additional 100 bytes FLASH - can read RTX formatted definitions
#endif

#ifdef SUPPORT_RTX_FORMAT
#define SUPPORT_RTX_EXTENSIONS
#endif

#define DEFAULT_DURATION 4
#define DEFAULT_OCTAVE 6
#define DEFAULT_BPM 63

#define RTX_STYLE_CONTINUOUS 'C'  // Tone length = note length
#define RTX_STYLE_NATURAL 'N'     // Tone length = note length - 1/16
#define RTX_STYLE_STACCATO 'S'    // Tone length = note length - 1/2
// my extensions :-)
#define RTX_STYLE_4 '4'           // Tone length = note length - 1/4
#define RTX_STYLE_8 '8'           // Tone length = note length - 1/8
#define RTX_STYLE_DEFAULT RTX_STYLE_NATURAL
#define RTTTL_STYLE_CONTINUOUS 0  // Tone length = note length
#define RTTTL_STYLE_NATURAL 16     // Tone length = note length - 1/16
#define RTTTL_STYLE_STACCATO 2    // Tone length = note length - 1/2
#define RTTTL_STYLE_4 4           // Tone length = note length - 1/4
#define RTTTL_STYLE_8 8           // Tone length = note length - 1/8
#define RTTTL_STYLE_DEFAULT RTTTL_STYLE_NATURAL

void setTonePinIsInverted(bool aTonePinIsInverted);

#ifdef SUPPORT_RTX_EXTENSIONS
void setNumberOfLoops(uint8_t aNumberOfLoops);
void setDefaultStyle(uint8_t aDefaultStyleDivisorValue);
uint8_t convertStyleCharacterToDivisorValue(char aStyleCharacter);
#endif

void getRtttlName(const char *aRTTTLArrayPtr, char * aBuffer, uint8_t aBuffersize);
void printName(const char *aRTTTLArrayPtr, Print * aSerial);

void startPlayRtttl(uint8_t aTonePin, const char *aRTTTLArrayPtr, void (*aOnComplete)()=NULL);
void playRtttlBlocking(uint8_t aTonePin, const char *aRTTTLArrayPtr);

void startPlayRandomRtttlFromArray(uint8_t aTonePin, const char* const aSongArray[], uint8_t aNumberOfEntriesInSongArray,
        char* aBufferPointer = NULL, uint8_t aBufferSize = 0, void (*aOnComplete)()=NULL);
void startPlayRandomRtttlFromArrayAndPrintName(uint8_t aTonePin, const char* const aSongArray[],
        uint8_t aNumberOfEntriesInSongArray, Print * aSerial, void (*aOnComplete)()=NULL);

void playRandomRtttlSampleBlocking(uint8_t aTonePin);
void playRandomRtttlSampleBlockingAndPrintName(uint8_t aTonePin, Print * aSerial);

void getRtttlNamePGM(const char *aRTTTLArrayPtrPGM, char * aBuffer, uint8_t aBuffersize);
void printNamePGM(const char *aRTTTLArrayPtrPGM, Print * aSerial);

void startPlayRtttlPGM(uint8_t aTonePin, const char *aRTTTLArrayPtrPGM, void (*aOnComplete)()=NULL);
void playRtttlBlockingPGM(uint8_t aTonePin, const char *aRTTTLArrayPtrPGM);

void startPlayRandomRtttlFromArrayPGM(uint8_t aTonePin, const char* const aSongArrayPGM[], uint8_t aNumberOfEntriesInSongArrayPGM,
        char* aBufferPointer = NULL, uint8_t aBufferSize = 0, void (*aOnComplete)()=NULL);
void startPlayRandomRtttlFromArrayPGMAndPrintName(uint8_t aTonePin, const char* const aSongArrayPGM[],
        uint8_t aNumberOfEntriesInSongArrayPGM, Print * aSerial, void (*aOnComplete)()=NULL);

void playRandomRtttlSampleBlockingPGM(uint8_t aTonePin);
void playRandomRtttlSampleBlockingPGMAndPrintName(uint8_t aTonePin, Print * aSerial);

// To be called from loop. - Returns true if tone is playing, false if tone has ended or stopped
bool updatePlayRtttl(void);

void stopPlayRtttl(void);

struct playRtttlState {
    long MillisOfNextAction;
    const char * NextTonePointer;

    struct {
        uint8_t IsRunning :1; // is false after boot
        uint8_t IsPGMMemory :1;
        uint8_t IsTonePinInverted :1; // True if tone pin has inverted logic i.e. is active on low.
    } Flags;

    // Tone pin to use for output
    uint8_t TonePin;
    // Callback on completion of tone
    void (*OnComplete)(void);

    uint8_t DefaultDuration;
    uint8_t DefaultOctave;
    long TimeForWholeNoteMillis;
#ifdef SUPPORT_RTX_EXTENSIONS
    uint8_t NumberOfLoops;  // 0 means forever, 1 means we are in the last loop
    // The divisor for the formula: Tone length = note length - note length * (1 / divisor)
    // If 0 then Tone length = note length;
    uint8_t StyleDivisorValue;
    const char * LastTonePointer; // used for loops

#endif
};
extern struct playRtttlState sPlayRtttlState;

#ifdef SUPPORT_RTX_EXTENSIONS
extern uint8_t sDefaultStyleDivisorValue;
#endif

extern const int Notes[] PROGMEM; // The frequencies of notes of the highest octave. Used to compute all other frequencies.
#define NOTES_OCTAVE 7 // Octave of the notes contained in Notes array above

/*
 * RTTTL format:
 * Prefix:
 *  Name
 *  Colon
 *  d=Default duration
 *  o=Default octave
 *  b=Beats per minutes (of quarter note)
 *  opt l=Number of loops
 *  opt s=Style - see "#define RTX_STYLE_CONTINUOUS 'C'" and following above
 *  Colon
 *
 * Note:
 *  opt duration
 *  note (p = pause)
 *  opt dot to increase duration by half
 *  opt octave
 */
/*
 * Disclaimer: These ringtone melodies are for personal enjoyment only. All copyright belongs to its respective author.
 */
#if !defined(__AVR__) && ! defined(PROGMEM)
#define PROGMEM
#endif

// Use rtx format to save space
static const char StarWars[] PROGMEM= "StarWars:d=32,o=5,b=45,l=2:p,f#,f#,f#,8b.,8f#.6,e6,d#6,c#6,8b.6,16f#.6,e6,d#6,c#6,8b.6,16f#.6,e6,d#6,e6,8c#6";
static const char Simpsons[] PROGMEM= "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
static const char PinkPanther[] PROGMEM= "PinkPanther:d=16,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,p,8f#,8g,p,8c6,8b,p,8d#,8e,p,8b,2a#,2p,a,g,e,d,2e";
static const char Wonderboy[] PROGMEM ="Wonderboy:d=4,o=5,b=225:f6,d6,f6,8d6,f6,32p,8f6,d6,f6,d6,e6,c6,e6,8c6,e6,32p,8e6,c6,e6,c6";
static const char AddamsFamily[] PROGMEM ="aadams:d=4,o=5,b=160:8c,f,8a,f,8c,b4,2g,8f,e,8g,e,8e4,a4,2f,8c,f,8a,f,8c,b4,2g,8f,e,8c,d,8e,1f,8c,8d,8e,8f,1p,8d,8e,8f#,8g,1p,8d,8e,8f#,8g,p,8d,8e,8f#,8g,p,8c,8d,8e,8f";
static const char SMB[] PROGMEM = "smb:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
static const char SMB_UNDER[] PROGMEM ="smb_under:d=4,o=6,b=100:32c,32p,32c7,32p,32a5,32p,32a,32p,32a#5,32p,32a#,2p,32c,32p,32c7,32p,32a5,32p,32a,32p,32a#5,32p,32a#,2p,32f5,32p,32f,32p,32d5,32p,32d,32p,32d#5,32p,32d#,2p,32f5,32p,32f,32p,32d5,32p,32d,32p,32d#5,32p,32d#";
static const char SMB_Death[] PROGMEM = "smbdeath:d=4,o=5,b=90:32c6,32c6,32c6,8p,16b,16f6,16p,16f6,16f.6,16e.6,16d6,16c6,16p,16e,16p,16c";
static const char TMNT[] PROGMEM  = "TMNT:d=4,o=5,b=100:8e,8f#,8e,8f#,8e,16f#,8e.,8f#,8g,8a,8g,8a,8g,16a,8g.,8a,8c6,8d6,8c6,8d6,8c6,16d6,8c.6,8d6,16a,16a,16a,16a,8g,8a,8p,16a,16a,16a,16a";
static const char PacMan[] PROGMEM  = "PacMan:d=32,o=5,b=112:32p,b,p,b6,p,f#6,p,d#6,p,b6,f#6,16p,16d#6,16p,c6,p,c7,p,g6,p,e6,p,c7,g6,16p,16e6,16p,b,p,b6,p,f#6,p,d#6,p,b6,f#6,16p,16d#6,16p,d#6,e6,f6,p,f6,f#6,g6,p,g6,g#6,a6,p,b.6";
static const char Aladin[] PROGMEM  = "WholeNewWorld:d=16,o=6,b=40:32p,g.,32f.,g#.,32g.,d#.,4a#5,g.,32f.,g#.,32g.,d#.,8g.,8f.,f.,32e.,g.,32f.,d.,f.,d#.,d.,d#.,32c.,d.,f.,d#.,8a#.5";
static const char Jura[] PROGMEM  = "JurassicPark:d=32,o=6,b=28:p,b5,a#5,8b5,16p,b5,a#5,8b5,16p,b5,a#5,16b.5,c#,16c#.,e,8e,16p,d#,b5,16c#.,a#5,16f#5,d#,b5,8c#,16p,f#,b5,16e.,d#,16d#.,c#,8c#";
static const char Batman[] PROGMEM  = "Batman:d=2,o=5,b=635:32p,e,e,d#,d#,d,d,d#,d#,e,e,d#,d#,d,d,d#,d#,a,a,g#,g#,g,g,g#,g#,a,a,g#,g#,g,g,g#,a,e,e,d#,d#,d,d,d#,d#,e,e,d#,d#,d,d,d#,d#,b,b,a#,a#,a,a,a#,b,a,a,g#,g#,g,g,g#,a,e,e,d#,d#,d,d,1d#,e,e";
static const char Hakuna[] PROGMEM  = "Hakuna:d=4,o=5,b=225:8c6,8d#6,p,8d#6,8p,8d#6,8d6,8p,2c6,2p,a,8c6,8d#6,8p,8d#6,8p,d#6,1c6,p,8p,8c6,8d#6,p,8d#6,8p,8d#6,8d6,8p,1c6,8p,a,8p,c6,8p,d#6,8p,d6,8p,1d6,2p,8e6,8g6,p,8g6,p,8a6,p,2a6,2p,a6,p,g6,8p,8d#6,8p,8d6,c6,1d6";
static const char GhostBuster[] PROGMEM  = "GhstBustrs:d=16,o=5,b=56:32c6,32c6,e6,c6,d6,a#,4p,32c6,32c6,32c6,32c6,a#,c6,4p,32c6,32c6,e6,c6,d6,a#,4p,32c6,32c6,32c6,32c6,a#,d6,c6";
static const char StarwarsI[] PROGMEM = "StarwarsI:d=16,o=5,b=100:4e,4e,4e,8c,p,g,4e,8c,p,g,4e,4p,4b,4b,4b,8c6,p,g,4d#,8c,p,g, 4e,8p";
static const char SpongeB[] PROGMEM = "SpongeB:d=4,o=6,b=180:d.,8d,8e,8d,8b5,8g5,8b5,8d,8e,8d,b5,8p,16p,g.,e.,d.,b5,8p,g.,e.,d.,b5,8p,d.,e.,p,8p,f_.,g,8p,16p,d.,8g,8a,8b,8a,8p,8b,g,32p,8d,g";
static const char DO[] PROGMEM = "DO:d=4,o=5,b=250:c";
static const char RE[] PROGMEM = "RE:d=4,o=5,b=250:d";
static const char MI[] PROGMEM = "MI:d=4,o=5,b=250:e";
static const char FA[] PROGMEM = "FA:d=4,o=5,b=250:f";
static const char SOL[] PROGMEM = "SOL:d=4,o=5,b=250:g";
static const char LA[] PROGMEM = "LA:d=4,o=5,b=250:a";
static const char SI[] PROGMEM = "SI:d=4,o=5,b=250:b";
/*
 * Array of songs. Useful for random melody
 */
//#pragma GCC diagnostic ignored "-Wunused-variable"
static const char * const RTTTLMelodies[] PROGMEM = { StarWars };
#define ARRAY_SIZE_MELODIES (sizeof(RTTTLMelodies)/sizeof(const char *)) // 21

#endif /* SRC_PLAYRTTTL_H_ */