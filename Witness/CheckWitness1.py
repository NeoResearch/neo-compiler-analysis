from boa.interop.Neo.Runtime import Notify, CheckWitness

def Main():
	OWNER=b'031a6c6fbbdf02ca351745fa86b9ba5a9452d785ac4f7fc2b7548ca2a46c4fcf4a'
	result = CheckWitness(OWNER)

	if result:
		print("OWNER is caller")
		return True
	return False


