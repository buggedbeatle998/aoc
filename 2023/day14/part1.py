def shift(rows, direction):
    for column_index in range(len(rows[0])) if direction in ["N","S"] else range(len(rows)):
        empty,polar=[],direction in ["N","S"]
        for row_index in (range(len(rows)) if direction=="N" else range(len(rows) - 1, -1, -1)) if direction in ["N","S"] else (range(len(rows[0])) if direction=="W" else range(len(rows[0]) - 1, -1, -1)):
            if (rows[row_index if polar else column_index][column_index if polar else row_index])!="O": empty=empty+[row_index if polar else column_index] if rows[row_index if polar else column_index][column_index if polar else row_index]=="." else []
            elif empty: rows[empty.pop(0) if polar else row_index][column_index if polar else empty.pop(0)],rows[row_index if polar else column_index][column_index if polar else row_index],empty="O",".",empty+[row_index if polar else column_index]

def shift_v(rows, direction):
    if direction == "N":
        row_order = range(len(rows))
    else:
        row_order = range(len(rows) - 1, -1, -1)

    for column_index in range(len(rows[0])):
        empty = []

        for row_index in row_order:
            match rows[row_index][column_index]:
                case ".":
                    empty.append(row_index)
                case "#":
                    empty = []
                case "O":
                    if empty:
                        rows[empty.pop(0)][column_index] = "O"
                        rows[row_index][column_index] = "."
                        empty.append(row_index)


def shift_h(rows, direction):
    if direction == "E":
        column_order = range(len(rows[0]) - 1, -1, -1)
    else:
        column_order = range(len(rows[0]))

    for row_index in range(len(rows)):
        empty = []

        for column_index in column_order:
            match rows[row_index][column_index]:
                case ".":
                    empty.append(column_index)
                case "#":
                    empty = []
                case "O":
                    if empty:
                        rows[row_index][empty.pop(0)] = "O"
                        rows[row_index][column_index] = "."
                        empty.append(column_index)

def calculate_load(rows):
    num_rows = len(rows)
    total_load = 0
    for i, row in enumerate(rows):
        total_load += len(list(filter(lambda r: r == "O", row))) * (num_rows - i)
    return total_load


def stringify(rows):
    return "".join(["".join(row) for row in rows])
rows = [list(line.strip("\n")) for line in open("data.txt").readlines()]

"""def north():
    shift_v(rows, "N")

def south():
    shift_v(rows, "S")

def east():
    shift_h(rows, "E")

def west():
    shift_h(rows, "W")

def spin_cycle():
    north()
    west()
    south()
    east()

cycles = []

spin_cycle()
while stringify(rows) not in cycles:
    cycles.append(stringify(rows))
    spin_cycle()

loop_length = len(cycles) - cycles.index(stringify(rows))
not_in_loop = cycles.index(stringify(rows))

cycles_left = (1_000_000_000 - not_in_loop) % loop_length

for i in range(cycles_left - 1):
    spin_cycle()"""
shift_v(rows,"N")
print(calculate_load(rows))