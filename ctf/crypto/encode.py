import string

eng_letters = string.ascii_lowercase
utf8_symbs = '󋛕Г⭼敬i񿖝񅱉Վ󆋼Ĩ󤶒䅒⣃𰋁רÈoL᪐c󨎋䤃uڳ'
subst = dict(zip(eng_letters, utf8_symbs))

with open('substituted_text.txt', 'r') as txt_from:
    with open('encoded_text.txt', 'w') as txt_to:
        txt_to.truncate()
        for letter in txt_from.read():
            if letter in subst:
                txt_to.write(subst[letter])
            else:
                txt_to.write(letter)

