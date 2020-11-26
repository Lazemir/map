from math import log, sqrt
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from matplotlib.collections import PatchCollection
from matplotlib.patches import Rectangle


def create_graphs(data):
    fig, (ax1, ax2, ax3) = plt.subplots(nrows=1, ncols=3, figsize=(10, 5))
    ax1.set_title("Insert N numbers")
    ax2.set_title("Insert one element")
    ax3.set_title("Erase one element")

    axes = [ax1, ax2, ax3]
    for i in range(len(data)):
        axes[i].scatter(data[i][0], data[i][1], marker='o')

        axes[i].xaxis.set_minor_locator(ticker.AutoMinorLocator())
        axes[i].yaxis.set_minor_locator(ticker.AutoMinorLocator())
        axes[i].grid(which="major", linewidth=1)
        axes[i].grid(which="minor", linestyle=':', linewidth=0.5)
    plt.show()


def create_main_data(filename):
    data = []
    with open(filename, 'r') as file:
        x = []
        y = []
        for line in file:
            block = (list(map(float, line.rstrip().split(" "))))
            x.append(block[0])
            y.append(block[1])
        data.append(x)
        data.append(y)
    return data


def main():
    data = [create_main_data("AVLT_insert_data.txt"),
            create_main_data("AVLT_insert_for_baby_data.txt"),
            create_main_data("AVLT_erase_data.txt")]
    # print(data)
    create_graphs(data)


if __name__ == '__main__':
    main()
