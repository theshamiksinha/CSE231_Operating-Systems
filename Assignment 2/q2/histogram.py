import matplotlib.pyplot as plt

elapsed_times = []

scheduling_policies = ['SCHED_OTHER', 'SCHED_RR', 'SCHED_FIFO']


with open('data.txt', 'r') as file:
    for line in file:
        parts = line.strip().split()
        if len(parts) == 2:
            policy, time_str = parts
            time_seconds = float(time_str)

            if policy == 'o':
                elapsed_time_sched_other = time_seconds
            elif policy == 'r':
                elapsed_time_sched_rr = time_seconds
            elif policy == 'f':
                elapsed_time_sched_fifo = time_seconds


elapsed_times.append(elapsed_time_sched_other)
elapsed_times.append(elapsed_time_sched_rr)
elapsed_times.append(elapsed_time_sched_fifo)

plt.bar(scheduling_policies, elapsed_times, color=['blue', 'green', 'red'])
plt.xlabel('Scheduling Policy')
plt.ylabel('Time to Complete (seconds)')
plt.title('Benchmarking Scheduling Policies')
plt.show()

with open('data.txt', 'w') as file:
    pass