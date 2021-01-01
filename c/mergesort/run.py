import datetime
import pathlib
import subprocess

i = 100

outputs = []
subprocess.run(['make', 'release'])
strategies = ['s', 'p']

while i < 1.1e10 + 1:
    for strategy in strategies:
        command = ['./mergesort', strategy, str(i)]
        print('INFO: Running command', ' '.join(command))
        out = subprocess.run(command, capture_output=True)

        if out.returncode == 0:
            outputs.append(out.stdout)
        else:
            print('WARN: mergesort returned non-zero return code. For n={: .2e}. '
                'Discarding result.'.format(i))

    i*=10

header = ' result,    strategy,        n,items_per_second,     malloc_time,  '
    'randomize_time,       sort_time'

for i in range(len(outputs)):
    outputs[i] = outputs[i].decode()

print('Results:')
csv_string = header + '\n' + ''.join(outputs)
print(csv_string)
csv_string = csv_string.replace(' ', '')

print('saving to disk...')

pathlib.Path('data').mkdir(parents=True, exist_ok=True)
date_str = datetime.datetime.now().strftime('%Y-%m-%d_%H%M')

with open('data/' + date_str + '.csv', 'w') as f:
    f.write(csv_string)
