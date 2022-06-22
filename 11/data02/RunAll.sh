shopt -s extglob
for f in !(*relu.py); do python3 "$f"; done