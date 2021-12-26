timer.Simple(0, engine.CloseServer)

assert(CI, 'tests expected to be running on configured dedicated server')

local function run_tests()
    require('network')
end

print('Running tests')
run_tests()
print('Tests are successful!')

file.Write('success.txt', GITHUB_SHA)