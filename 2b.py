

fd = open("2b.in")
# Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
total = 0
for i, line in enumerate(fd.readlines(), start=1):
    min_required = {
        "red": 0, "blue": 0, "green": 0
    }
    for bag in line.strip().split(": ")[1].split("; "):
        for ball_info in bag.split(", "):
            str_count, str_color = ball_info.split(" ")
            min_required[str_color] = max(min_required[str_color], int(str_count))
    multiple = 1
    for k, v in min_required.items():
        if v != 0:
            multiple *= v
    total += multiple
    print(line, multiple)
print(total)