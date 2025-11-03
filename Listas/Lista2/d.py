def fat():
    num=int(input("Digite um numro: "))
    soma =1
    for i in range(num):
        soma *= i+1 
    print(f"{soma}")
fat()
