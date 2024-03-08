#!/usr/bin/bash

mkdir -p Result

> Result/output.txt

while IFS=" " read -r a b op; do

    if [ "${op,,}" = "xor" ]; then
        result=$(echo "$a ^ $b" | bc)
        echo "Result of xor $a $b: $result" >> Result/output.txt

    elif [ "${op,,}" = "product" ]; then
        result=$(echo "$a * $b" | bc)
        echo "Result of Product $a $b: $result" >> Result/output.txt

    elif [ "${op,,}" = "compare" ]; then

        if (( $(echo "$a > $b" | bc -l) )); then

            result=$a
            echo "Result of Compare $a $b: $result" >> Result/output.txt

        else

            result=$b
            echo "Result of Compare $a $b: $result" >> Result/output.txt

        fi

    else

        echo "INVALID INPUT IN FILE" >> Result/output.txt

    fi

done < input.txt
