import pandas as pd
import matplotlib.pyplot as plt

file_prefix = 'data/2021-01-01_1325'
df = pd.read_csv(file_prefix + '.csv')
df_sequential = df[df['strategy'] == 'sequential']
df_parallel = df[df['strategy'] == 'parallel']

plt.figure(figsize=(10,7))
plt.plot(df_sequential['n'], df_sequential['items_per_second'])
plt.plot(df_parallel['n'], df_parallel['items_per_second'])
plt.title("Items per second for different array sizes")
plt.ylabel("items per second sorted")
plt.xlabel("array size")
plt.legend(["sequential", "parallel"])
plt.savefig(file_prefix + '_items_per_second.png')

plt.figure(figsize=(10,7))
plt.plot(df_sequential['n'], df_sequential['sort_time'])
plt.plot(df_parallel['n'], df_parallel['sort_time'])
plt.title("Time taken for different array sizes")
plt.ylabel("time to sort")
plt.xlabel("array size")
plt.legend(["sequential", "parallel"])
plt.savefig(file_prefix + '_time_taken.png')
