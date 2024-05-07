# testing.awk

{
  if (FNR == NR) {
    # First file processing
    words[$1] = $0  # Store the whole line using the word as a key
  } else {
    # Second file processing (expected)
    if ($1 in words) {
      match = 1  # Word exists in the first file
    } else {
      match = 0  # Word doesn't exist in the first file
    }

    if (match) {
      # When there's a match, print the matching line
      print $0
    } else {
      # When no match is found, print a warning
      print "No match found for: " $0
    }
  }
}
