import re

x = ""
with open("input.txt", "r+") as f:
    x = f.read()
    x = x.replace("seeds: ", "")
    for match in re.findall("\w+-\w+-\w+ map:", x):
        x = x.replace(match, "")
    x = x.replace("\n", " ").replace("   ", "#")

    f.seek(0)  # sets point at the beginning of the file
    f.truncate(0)  # clear previous content
    f.write(x)
