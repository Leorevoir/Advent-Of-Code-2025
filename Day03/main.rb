def get_file_content(filename)
  File.read(filename).split("\n")
end

def max_joltage(line, k)
  n = line.size
  dp = Array.new(k + 1) { Array.new(n, 0) }

  n.times { |i| dp[1][i] = line[i].to_i }

  (2..k).each { |length|
    (length-1...n).each { |i|
      max_prev = (0...(i)).map { |j| dp[length-1][j] }.max
      dp[length][i] = max_prev * 10 + line[i].to_i
    }
  }

  dp[k].max
end

if __FILE__ == $0
  unless ARGV.empty?
    part_1 = 0
    part_2 = 0

    get_file_content(ARGV[0]).each { |line|
      part_1 += max_joltage(line, 2)
      part_2 += max_joltage(line, 12)
    }
    puts part_1
    puts part_2
  end
end
