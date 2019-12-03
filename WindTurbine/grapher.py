#%%
import math
import os
import re
import numpy as np
import matplotlib.pyplot as plt

#%%
# Read file
print("Scanning for .CSV files...")
files = sorted(tuple(os.walk("."))[0][2])
csvFileScanner = re.compile("\\.(csv|CSV)$")
csvFiles = []
for f in files:
    if csvFileScanner.search(f):
        csvFiles.append(f)
# Select file
def selectFiles():
    global csvFiles
    digitLength = max((math.ceil(math.log(len(csvFiles), 10)), len("ALL"))) + 2
    print("Select files (space-delimited IDs or 'ALL', case-insensitive):")
    print("\n".join(["{:>{:d}d}: {:s}".format(i + 1, digitLength, csvFiles[i]) for i in range(len(csvFiles))]))
    print("{:>{:d}s}: ALL".format("ALL", digitLength))
    res = input().upper().split()
    if res == [] or res == [""]:
        print("No files selected.")
        exit(0)
    if res[0] == "ALL":
        return np.arange(len(csvFiles))
    try:
        res = np.array(res).astype(int)
        if np.all(0 < res) and np.all(res <= len(csvFiles)):
            # OK
            return np.unique(res) - 1
        print("ERROR: file index out of range.")
        exit(1)
    except Exception as e:
        print("ERROR: {}".format(e))
        exit(1)

selectedFiles = selectFiles()
# print(selectedFiles)

#%%
# Make single graph
def graph(fileName, no0 = False, logScale = False):
    with open(fileName, 'r') as f:
        content = f.read().strip()
        content = content.split('\n')[1:]
        content = [line.split(',') for line in content]
        ids = np.array([int(line[0]) for line in content])
        val = np.array([float(line[1]) for line in content])
        if no0:
            ids = ids[1:]
            val = val[1:]
        if logScale:
            np.place(val, val == 0, [np.nan])
            val = np.log(val) / math.log(10)
        non0IDs = np.extract(val != 0, ids)
        # with 0
        plt.figure()
        if len(non0IDs):
            maxNon0 = np.max(non0IDs)
            plt.scatter(ids[:maxNon0 + 1], val[:maxNon0 + 1], color=(0,0,0), s=4)  # Adjust graph type here
            if logScale:
                ytickLoc = plt.yticks()[0]
                plt.yticks(ytickLoc, ["$10^{{{:.1f}}}$".format(i) for i in ytickLoc])
        else:
            plt.text(0, 0, "ALL ZERO")
        plt.savefig(fileName + (".no0" if no0 else "") + (".logScale" if logScale else "") + ".png", dpi=144)
        return 0
    print("Something went wrong when graphing " + fileName)
    return 2

no0 = input("No 0 <false> (\"both\" for both):")
logScale = input("Logarithmic scale <false> (\"both\" for both):")

for i in selectedFiles:
    if no0 == "both":
        if logScale == "both":
            graph(csvFiles[i])
            graph(csvFiles[i], no0 = True)
            graph(csvFiles[i], logScale = True)
            graph(csvFiles[i], no0 = True, logScale = True)
        else:
            graph(csvFiles[i], logScale = logScale)
            graph(csvFiles[i], no0 = True, logScale = logScale)
    elif logScale == "both":
        graph(csvFiles[i], no0 = no0)
        graph(csvFiles[i], no0 = no0, logScale = True)
    else:
        graph(csvFiles[i], no0 = no0, logScale = logScale)
