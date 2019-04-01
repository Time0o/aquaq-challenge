#!/bin/sh

# project structure ############################################################

INPUT_DIR=inputs
OUTPUT_DIR=outputs
CPP_DIR=cpp

# utility display functions ####################################################

TEXTBOLD=$(tput bold)
TEXTRED=$(tput setaf 1)
TEXTGREEN=$(tput setaf 2)
TEXTBLUE=$(tput setaf 4)
TEXTWHITE=$(tput setaf 7)
TEXTRESET=$(tput sgr0)

print_header() {
    echo -n ${TEXTBOLD}${TEXTBLUE}

    frame=$(printf '=%.0s' $(seq 1 $((${#1} + 4))))

cat << EOF
$frame
| $1 |
$frame
EOF

    echo -n ${TEXTRESET}
}

print_info() {
    echo -n ${TEXTBOLD}${TEXTWHITE}
    echo -e "$1"
    echo -n ${TEXTRESET}
}

print_success() {
    echo -n ${TEXTBOLD}${TEXTGREEN}
    echo -e "$1"
    echo -n ${TEXTRESET}
}

print_failure() {
    echo -n ${TEXTBOLD}${TEXTRED}
    echo -e "$1"
    echo -n ${TEXTRESET}
}

# C++ ##########################################################################

## build
print_header "building C++ solutions"

(cd $CPP_DIR; make)

if [ $? -ne 0 ]; then
    echo "C++ build failed" 2>&1
    exit 1
fi

## run tests
print_header "testing C++ solutions"

for prog_path in $CPP_DIR/bin/*; do
    if [[ "$prog_path" == *.d ]]; then
        continue
    fi

    prog="$(basename $prog_path)"
    print_info "$prog"

    output="$(cat "$INPUT_DIR/$prog.txt" | "$prog_path")"

    if [ $? -ne 0 ]; then
        print_failure "==> program execution failed"
    else
        expected="$(cat $OUTPUT_DIR/$prog.txt)"

        if [ "$output" == "$expected" ]; then
            print_success "==> success"
        else
            print_failure "expected:"
            echo "$expected"
            print_failure "but got:"
            echo "$output"
            print_failure "==> failure"
        fi
    fi
done
