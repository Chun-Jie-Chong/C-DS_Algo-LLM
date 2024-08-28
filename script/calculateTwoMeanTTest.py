from scipy import stats
import numpy as np

# Complexity
ds_algo_chatgpt_complexity = [4, 6, 7, 9, 9, 10, 11, 18, 20, 22, 25, 29, 29, 58, 124]
ds_algo_human_complexity = [7, 12, 4, 25, 6, 21, 37, 19, 28, 8, 49, 52, 37, 70, 189]
crypto_chatgpt_complexity = [7, 9, 65]
crypto_human_complexity = [12, 8, 37]
# data1 = ds_algo_chatgpt_complexity + crypto_chatgpt_complexity
# data2 = ds_algo_human_complexity + crypto_human_complexity

# Complexity per code
ds_algo_chatgpt_complexity_per_loc = [0.109375, 0.11392405063291139, 0.12121212121212122, 0.13432835820895522, 0.14285714285714285, 0.19607843137254902, 0.22784810126582278, 0.2358490566037736, 0.24390243902439024, 0.25, 0.26126126126126126, 0.2619047619047619, 0.27358490566037735, 0.3515151515151515, 0.4881889763779528]
ds_algo_human_complexity_per_loc = [0.07272727272727272, 0.3472222222222222, 0.1346153846153846, 0.12, 0.1608695652173913, 0.21428571428571427, 0.11728395061728394, 0.1891891891891892, 0.17073170731707318, 0.16901408450704225, 0.27205882352941174, 0.1038961038961039, 0.2613065326633166, 0.22151898734177214, 0.3197969543147208]
crypto_chatgpt_complexity_per_loc = [0.04, 0.08, 0.33]
crypto_human_complexity_per_loc = [0.07, 0.07, 0.06]
data1 = ds_algo_chatgpt_complexity_per_loc + crypto_chatgpt_complexity_per_loc
data2 = ds_algo_human_complexity_per_loc + crypto_human_complexity_per_loc

# Perform t-test
t_stat, p_value = stats.ttest_ind(data1, data2)

print(f"T-statistic: {t_stat}")
print(f"P-value: {p_value}")
print(f"Mean of ChatGPT-4o: {np.mean(data1)}")
print(f"Mean of Human: {np.mean(data2)}")
print(f'Median of ChatGPT-4o: {np.median(data1)}')
print(f'Median of Human: {np.median(data2)}')
print(f'Geometric mean of ChatGPT-4o: {stats.gmean(data1)}')
print(f'Geometric mean of Human: {stats.gmean(data2)}')
print(f'Trimmed mean of ChatGPT-4o at 5%: {stats.trim_mean(data1, 0.05)}')
print(f'Trimmed mean of Human at 5%: {stats.trim_mean(data2, 0.05)}')
print(f'Trimmed mean of ChatGPT-4o at 10%: {stats.trim_mean(data1, 0.1)}')
print(f'Trimmed mean of Human at 10%: {stats.trim_mean(data2, 0.1)}')
print(f'Trimmed mean of ChatGPT-4o at 15%: {stats.trim_mean(data1, 0.15)}')
print(f'Trimmed mean of Human at 15%: {stats.trim_mean(data2, 0.15)}')