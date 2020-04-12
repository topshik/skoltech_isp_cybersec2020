string = 'cp'


for i in range(16):
    if i % 2 == 0:
        string = string + chr(ord(string[i]) + 2)
    else:
        string = string + chr(ord(string[i]) - 1)

def checksum(string):
    res = 0
    for elem in string:
        res += ord(elem) ** 2
    return res

print(string, checksum(string))
