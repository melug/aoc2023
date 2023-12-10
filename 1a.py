
fd = open("1a.in")
total = 0
for line in fd.readlines():
    first_digit, last_digit = None, None
    for c in line:
        if c.isdigit():
            if first_digit is None:
                first_digit = int(c)
            last_digit = int(c)
    total += 10*first_digit + last_digit
print(total)