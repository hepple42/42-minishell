# **************************************************************************** #
#	WILD  																       #
# **************************************************************************** #

grep 42 < in | wc -l && ( /bin/echo 1 2 3 4 > tmp_out || /bin/echo 2 > tmp_out >> tmp_out tmp_out )
rm -f tmp_out
