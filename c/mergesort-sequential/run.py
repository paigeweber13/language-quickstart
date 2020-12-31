import subprocess

i = 1

outputs = []
subprocess.run(['make', 'release'])

while i < 1.1e9:
    command = ['./mergesort', str(i)]
    print('INFO: Running command', ' '.join(command))
    out = subprocess.run(command, capture_output=True)

    if out.returncode == 0:
        outputs.append(out.stdout)
    else:
        print('WARN: mergesort returned non-zero return code. For n={: .2e}. '
            'Discarding result.'.format(i))

    i*=10

print(outputs)
