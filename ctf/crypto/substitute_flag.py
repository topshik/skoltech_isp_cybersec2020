# flag: skoltech{00h_y0u_4r3_my_1i7713_cryp70gr4ph3r}

subst = {' ': '_', 'o': '0', 'a': '4', 'e': '3', 'l': '1', 't': '7'}
flag = 'skoltech{00h_y0u_4r3_my_1i7713_cryp70gr4ph3r}'
result = ''
dist = 30
cnt = 0
symbols_substituted = 0

with open('frequency.txt', 'r') as f:
    data = f.read()
    for letter in data:
        if symbols_substituted == len(flag):
            result += letter
            continue
        if symbols_substituted < 9:
            if cnt > dist and flag[symbols_substituted] != letter:
                result += flag[symbols_substituted]
                symbols_substituted += 1
                cnt = 0
            else:
                result += letter
                cnt += 1
        else:
            # print(letter)
            if cnt > dist and flag[symbols_substituted] != letter:
                if letter in subst and subst[letter] == flag[symbols_substituted]:
                    result += flag[symbols_substituted]
                    symbols_substituted += 1
                    cnt = 0
                else:
                    result += flag[symbols_substituted]
                    symbols_substituted += 1
                    cnt = 0
            else:
                result += letter
                cnt += 1

    with open('substituted_text.txt', 'w') as res:
        res.truncate()
        res.write(result)

print(symbols_substituted)
