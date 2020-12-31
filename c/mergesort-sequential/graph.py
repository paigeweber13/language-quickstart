import pandas as pd
import matplotlib.pyplot as plt

file_prefix = 'data/2020-12-31_1821'
df = pd.read_csv(file_prefix + '.csv')

plt.figure(figsize=(10,7))
plt.plot(df['n'], df['items_per_second'])
plt.title("Items per second for different array sizes")
plt.ylabel("items per second sorted")
plt.xlabel("array size")
plt.savefig(file_prefix + '_items_per_second.png')

plt.figure(figsize=(10,7))
plt.plot(df['n'], df['sort_time'])
plt.title("Time taken for different array sizes")
plt.ylabel("time to sort")
plt.xlabel("array size")
plt.savefig(file_prefix + '_time_taken.png')
