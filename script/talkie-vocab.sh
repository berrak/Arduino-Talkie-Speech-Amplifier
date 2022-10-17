#!/bin/bash

# File: talkie-vocab.sh
#
# View the predefined vocabulary in the Arduino Speech
# library Talkie (https://github.com/ArminJo/Talkie).
# Copyright 2011 Peter Knight
# Copyright 2019 Armin Joachimsmeyer
#
# Author: Debinix Team (c). GPL-3.0 license.
# Minor modification in the used text strings.
# Date: 2022-10-15.

ARDUINOTALKIE="/libraries/Talkie"
CWD=$(pwd)

function AstroBlaster() {
    clear
    echo "#include \"Vocab_AstroBlaster.h\""
    echo "Game sounds extracted by Richard Broadhurst."
    echo "https://www.youtube.com/watch?v=IHldh_rknuk&feature=youtu.be&t=12"

    echo -e "\n\n\t\tHit any key to list sounds ...\n"
    read -r -s -n 1
    grep -n "\[\]" Vocab_AstroBlaster.cpp | cut -d' ' -f 4 | cut -d'[' -f 1
}

function Soundbites() {
    clear
    echo "#include \"Vocab_Soundbites.h\""
    echo "Sound bites from SPROW's custom BBC Micro phrase ROM."

    echo -e "\n\n\t\tHit any key to list sounds ...\n"
    read -r -s -n 1
    grep -n "\[\]" Vocab_Soundbites.h | cut -d'[' -f 1 | cut -d' ' -f 4
}

function Special() {
    clear
    echo "#include \"Vocab_Special.h\""
    echo "A collection of 'special sounds'."

    echo -e "\n\n\t\tHit any key to list sounds ...\n"
    read -r -s -n 1
    grep -n "\[\]" Vocab_Special.h | cut -d'[' -f 1 | cut -d' ' -f 4
}

function US_Acorn() {
    clear
    echo "#include \"Vocab_US_Acorn.h\""
    echo "A male UK english voice. 165 words related to home computing. Data originally part of"
    echo "Acorn Computers Speech Synthesizer, and famously voiced by BBC's Kenneth Kendall."

    echo -e "\n\n\t\tHit any key to list all words ...\n"
    read -r -s -n 1
    grep -n "\[\]" Vocab_US_Acorn.h | cut -d'[' -f 1 | cut -d' ' -f 4 | more
}

function US_Clock() {
    clear
    echo "#include \"Vocab_US_Clock.h\""
    echo "A female US english voice. 35 words related to time of day."
    echo "Data of unknown origin from ROM serial number VM71003A."

    echo -e "\n\n\t\tHit any key to list all words ...\n"
    read -r -s -n 1
    grep -n "\[\]" Vocab_US_Clock.h | cut -d'[' -f 1 | cut -d' ' -f 4 | more
}

function US_Large() {
    clear
    echo "#include \"Vocab_US_Large.h\""
    echo "A male US english voice. Over 600+ words related to aeronautics."
    echo "Data of unknown origin. ROM serial number VM61002, VM61003, VM61004 and VM61005."

    echo -e "\n\n\t\tHit any key to list all words ...\n"
    read -r -s -n 1
    grep -n "\[\]" Vocab_US_Large.h | cut -d'[' -f 1 | cut -d' ' -f 4 | more
}

function US_Large_sorted() {
    clear
    echo "#include \"Vocab_US_Large.h\""
    echo "A male US english voice. Over 600+ words related to aeronautics."
    echo "Data of unknown origin. ROM serial number VM61002, VM61003, VM61004 and VM61005."

    echo -e "\n\n\t\tHit any key to list all words ...\n"
    read -r -s -n 1
    grep -n "\[\]" Vocab_US_Large.h | cut -d'[' -f 1 | cut -d' ' -f 4 | sort | more
}

function US_TI99() {
    clear
    echo "#include \"Vocab_US_TI99.h\""
    echo "A deep male US english voice. 360+ words related to home computing."
    echo "Data originally part of Texas Instruments TI-99/4A Speech System."

    echo -e "\n\n\t\tHit any key to list all words ...\n"
    read -r -s -n 1
    grep -n "\[\]" Vocab_US_TI99.h | cut -d'[' -f 1 | cut -d' ' -f 4 | more
}

function searchterm() {
    clear
    echo -n "Enter a word (upper case) to search for: "
    read -r -e myword
    #echo "'$myword'"
    grep --color=always -n "$myword" Vocab_*.h | more
}

function menu() {
    clear
    echo
    echo -e "\tTalkie Predefined Vocabulary Information\n"
    echo -e "\t1. AstroBlaster - sounds"
    echo -e "\t2. Soundbites -sounds"
    echo -e "\t3. Special - sounds"
    echo -e "\t4. US_Acorn - voices"
    echo -e "\t5. US_Clock -voices"
    echo -e "\t6. US_Large - voices"
    echo -e "\t7. US_Large sorted - voices"
    echo -e "\t8. US_TI99 - voices\n"

    echo -e "\t9. Grep search word\n"

    echo -e "\n\t0. Exit program\n\n"
    echo -en "\t\tEnter option: "
    read -r -n 1 option
}

# Test if grep is installed
grep --version >/dev/null 2>&1
if [ ! "$?" ]
then
    echo "Pre-requisite 'grep' is not installed. Install 'grep' and retry."
    exit 1
fi

# Test if more is installed
more --version >/dev/null 2>&1
if [ ! "$?" ]
then
    echo "Pre-requisite 'more' is not installed. Install the package 'util-linux' and retry."
    exit 1
fi

# Test command argument. Given in the Arduino IDE in File -> preferences.
case $# in
    0)  echo "Missing the Arduino Sketchbooks location as the first argument. Aborting!"
        echo "Open Arduino IDE, use the Sketchbook path from File->Preferences, and try again."
        exit 1 ;;
    1) SKETCHBOOK=$1
        ;;
    *)  echo "Give the Sketchbook path as the only argument."
        exit 1 ;;
esac


# Find out if the Arduino sketchbook exist, and if Talkie is installed in the library location
if [ ! -d "$SKETCHBOOK" ];then
    echo "The given Arduino Sketchbooks location '$SKETCHBOOK' does not exist. Therefore, the script is terminating now."
    exit 1
else
    if [ ! -d "$SKETCHBOOK/$ARDUINOTALKIE" ]; then
        echo "The 'Talkie' library is missing. Install the library with Arduino IDE and retry."
        exit 1
    else
        cd "$SKETCHBOOK/$ARDUINOTALKIE"/src || exit 1
    fi
fi

# The MAIN menu
while true
do
    menu
    case $option in
        0)
            break ;;
        1)
            AstroBlaster ;;
        2)
            Soundbites ;;
        3)
            Special ;;
        4)
            US_Acorn ;;
        5)
            US_Clock ;;
        6)
            US_Large ;;
        7)
            US_Large_sorted ;;
        8)
            US_TI99 ;;
        9)
            searchterm ;;
        *)
            clear
            echo "Sorry, wrong selection" ;;

    esac
    echo -en "\n\n\t\tHit any key to continue..."
    read -r -n 1
    clear

done

# Restore directory at start
cd "$CWD" || exit 1

clear

# EOF
