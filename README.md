Welcome, humanoid

git upload shortcut:
git config --global alias.upload '!git add . && git commit -m "wip" && git push'

make re && valgrind --leak-check=full --show-leak-kinds=definite,possible ./minishell 2> valgrind.txt


