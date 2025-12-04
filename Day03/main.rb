def get_file_content(filename)
  File.read(filename).split("\n")
end

if __FILE__ == $0
  total = get_file_content(ARGV[0]).sum { |line|
    line.chars.each_with_index.map { |c, i|
      line[(i+1)..].chars.map { |d| c + d }.map(&:to_i)
    }.flatten.max
  } unless ARGV.empty?
  puts total
end

