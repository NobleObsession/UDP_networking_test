def check_output_file():
	previous_index = -1
	output_file = open('processed_packets.txt', 'r')
	for line in output_file:
		parsed_line = line.split(' ', 1)
		if (int(parsed_line[0]) - previous_index) != 1:
			return False
		else:
			previous_index = previous_index + 1
			continue
	return True

if check_output_file():
	print("SUCCESS: normal order of packets")
else:
	print("FAIL: wrong order of packets")