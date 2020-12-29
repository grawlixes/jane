for target in range(1, 11 + 1):
    numbers = list(range(1, 2000 + 1))

    toDelete = 0

    while numbers[toDelete] != target:
        app = []
        for i in range(toDelete):
            app.append(numbers[toDelete - i - 1])
            app.append(numbers[toDelete + i + 1])

        numbers = app + numbers[2*toDelete + 1:]
        toDelete += 1

    print("Solution for " + str(target) + " = " + str(toDelete + 1))
