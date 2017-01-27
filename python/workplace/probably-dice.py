
def possibilities(dice_number, sides, target):
    if target < dice_number or dice_number * sides < target:
        return 0

    if dice_number == 1:
        return 1

    min_value = sides - (dice_number * sides - target) if sides - (dice_number * sides - target)  > 0 else 1
    max_value = sides if target - dice_number >= sides else target - dice_number + 1
    A = 0
    for i in range(min_value,max_value + 1):
        A += possibilities(dice_number - 1, sides, target - i)
    return A


def probability(dice_number, sides, target):
    omega = sides ** dice_number
    A = possibilities(dice_number, sides, target)
    return A / omega

if __name__ == '__main__':
    #These are only used for self-checking and are not necessary for auto-testing
    def almost_equal(checked, correct, significant_digits=4):
        precision = 0.1 ** significant_digits
        return correct - precision < checked < correct + precision
        
    assert(almost_equal(probability(2, 6, 3), 0.0556)), "Basic example"
    assert(almost_equal(probability(2, 6, 4), 0.0833)), "More points"
    assert(almost_equal(probability(2, 6, 7), 0.1667)), "Maximum for two 6-sided dice"
    assert(almost_equal(probability(2, 3, 5), 0.2222)), "Small dice"
    assert(almost_equal(probability(2, 3, 7), 0.0000)), "Never!"
    assert(almost_equal(probability(3, 6, 7), 0.0694)), "Three dice"
    assert(almost_equal(probability(10, 10, 50), 0.0375)), "Many dice, many sides"
