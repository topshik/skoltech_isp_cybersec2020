import os

FLAG = os.environ["FLAG"]

source = input("Input your solution (only one line is allowed): ")

for banned in ["globals", "FLAG", "os", "open"]:
    if banned in source:
        print("Hacker detected!")
        exit(1)

exec(source)
