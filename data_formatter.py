import binascii


class Hit:
    def __init__(self, data):
        hex_data = binascii.hexlify(data)
        s = format(int(hex_data, 16), '#018b')[2:]
        self.x = int(s[-3:], 2)
        self.y = int(s[-6:-3], 2)
        self.tdc = int(s[:-6], 2)

    def __repr__(self):
        return "%d %d %d" % (self.tdc, self.y, self.x)


def readFile(filename):
    hits = []
    with open(filename, "rb") as f:
        while True:
            bytes = f.read(2)
            if bytes == "":
                break
            hits.append(Hit(bytes))
    return hits


def main():
    hits = [i.x for i in readFile('onetrack.raw')]
    print(hits)

if __name__ == '__main__':
    main()
