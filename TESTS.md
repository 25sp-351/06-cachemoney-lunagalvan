1. Zero value
   - Input: 0
   - Expected: "zero dollars"

2. Single cent
   - Input: 1
   - Expected: "one cent"

3. Single dollar
   - Input: 100
   - Expected: "one dollar"

4. Dollar and cents
   - Input: 101
   - Expected: "one dollar and one cent"

5. Complex case
   - Input: 122309
   - Expected: "one thousand two hundred twenty-three dollars and nine cents"

6. Another complex case
   - Input: 473434
   - Expected: "four thousand seven hundred thirty-four dollars and thirty-four cents"

7. Large number
   - Input: 1000000
   - Expected: "ten thousand dollars"

chmod +x tests.sh
./tests.sh

Expected output: "success" if all tests pass
