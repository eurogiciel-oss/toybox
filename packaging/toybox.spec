Name: toybox
Version: 0.4.9
Release: 1%{?dist}
Summary: ToyBox GNU Core utilities
Group: Base/Utilities
License: BSD-2-Clause-FreeBSD
URL: http://landley.net/toybox/about.html
Source: http://landley.net/toybox/downloads/toybox-0.4.9.tar.bz2
Source1: config

%description
Toybox combines the most common Linux command line utilities together into a single BSD-licensed executable

%prep
cp %{SOURCE1} ./.config
%autosetup

%build
make toybox %{?_smp_mflags}

%install
%make_install
make install

%files
%doc

%changelog
