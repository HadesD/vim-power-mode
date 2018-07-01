if exists('g:loaded_power_mode')
  finish
end

let g:loaded_power_mode = 1

let s:exe = fnamemodify(expand('<sfile>:h:h') . '/particle.exe', ':p')
if !filereadable(s:exe)
  finish
end

function! s:rand() abort
  return reltimestr(reltime())[-2:]
endfunction

function! s:wait(mil)
  let timetowait = a:mil . " m"
  exe 'sleep '.timetowait
endfunction

let [s:oldx, s:oldy] = [getwinposx(), getwinposy()]
function! s:set_oldpos()
  let [s:oldx, s:oldy] = [getwinposx(), getwinposy()]
endfunction

au VimEnter * call s:set_oldpos()

let s:ctb = [
      \ '000000', 'aa0000', '00aa00', '0000aa', 'aa5500', 'aa00aa', '00aaaa', 'aaaaaa',
      \ '555555', 'ff5555', '55ff55', 'ffff55', '5555ff', 'ff55ff', '55ffff', 'ffffff'
      \ ]
function! s:particle()
  let c = synIDattr(synIDtrans(synID(line("."), col(".")-1, 1)), "fg")
  if c =~ '^#'
    let c = c[1:]
  elseif c =~ '^[0-9]\+$'
    let c = get(s:ctb, c, s:ctb[-1])
  else
    let c = 'ffffff'
  endif
  let [x, y] = [screencol(), screenrow()]
  if x == 10000 || y == 10000
    let [x, y] = [s:oldx, s:oldy]
  endif
  let cmd = printf("%s %d,%d,%d,%d,%d %s", s:exe, v:windowid, x, y, &columns, &lines, c)
  if (executable('wine'))
    let cmd = 'wine ' . cmd
  end
  if exists(':AsyncRun')
    silent exe 'AsyncRun! ' cmd
  else
    silent exe "!start" cmd
  end
endfunction

function! s:power_mode()
  let [x, y] = [getwinposx(), getwinposy()]
  let x += s:rand() % 10 - 6
  let y += s:rand() % 10 - 6
  exe 'winpos ' . x . ' '. y
  call s:wait(5)
  exe 'winpos ' s:oldx . ' ' . s:oldy
  call s:particle()
endfunction

function! s:install(flag)
  augroup ActivePowerMode
    au!
    if a:flag
      au TextChangedI * call s:power_mode()
      au VimResized * call s:set_oldpos()
    endif
  augroup END
endfunction

call <SID>install(1)

command! -nargs=0 PowerModeOn call <SID>install(1)
command! -nargs=0 PowerModeOff call <SID>install(0)

