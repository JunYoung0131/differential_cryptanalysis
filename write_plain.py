import random

print("작성 시작")
b = []
f = open("./PlainText.txt", 'w')
count = 0

while True:
    if count == 10000:
        break
    else:
        x = random.randrange(0x0, 0x100000000)
        if x in b:
            continue
        else:
            x_star = x ^ 0x0000000F
            f.write("%X\n" % x)
            f.write("%X\n" % x_star)
            b.append(x)
            count = count+1

f.close()

print("작성 완료")
