Name:           15_puzzle
Version:        1.0
Release:        1%{?dist}
Summary:        Simple C/C++ based 15 puzzle solver

License:        MIT
URL:            https://github.com/githubtestprojects/15_puzzle
Source0:        %{name}-%{version}.tar.gz


Requires:  gcc
Requires:  make

%description
This is a simple C/C++ based 15 puzzle solver. It uses the A* algo to solve the puzzle.

%prep
%setup -q -n 15_puzzle-1.0



%build
make 

%install
#cp the run file from rpmbuild/BUILD/%{name}-%{version}/run to /usr/bin
install -Dm755 run %{buildroot}%{_bindir}/%{name}

%files
%license LICENSE
%{_bindir}/%{name}

%changelog
* Fri Mar 30 2024 Rostant Alimeta <rostant.alimeta@gmail.com> - 1.0-1
- Initial packaging of the puzzle solver
