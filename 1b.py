
fd = open("1b.in")
total = 0
numbers = [
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
]
for line in fd.readlines():
    first_digit, last_digit = None, None
    for i, c in enumerate(line):
        if c.isdigit():
            if first_digit is None:
                first_digit = int(c)
            last_digit = int(c)
        else:
            for number in numbers:
                if line[i:].startswith(number):
                    if first_digit is None:
                        first_digit = numbers.index(number)+1
                    last_digit = numbers.index(number)+1
    n = 10*first_digit+last_digit
    print(n)
    total += n
print(total)