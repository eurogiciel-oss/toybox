Name: toybox
Version: 0.4.9
Release: 1%{?dist}
Summary: ToyBox Core utilities
Group: Base/Utilities
License: BSD-2-Clause-FreeBSD
URL: http://landley.net/toybox/about.html
Source: http://landley.net/toybox/downloads/toybox-0.4.9.tar.bz2
Source1: config

%description
Toybox combines the most common Linux command line utilities together into a single BSD-licensed executable

%prep
%autosetup

%build
cp %{SOURCE1} ./.config
make %{?_smp_mflags} toybox

%install
make PREFIX=./ install
mkdir -p %{buildroot}%{_bindir}
mkdir -p %{buildroot}%{_sbindir}
cp --preserve=links ./bin/* %{buildroot}%{_bindir}
cp --preserve=links ./sbin/* %{buildroot}%{_sbindir}

%files
%{_bindir}/*
%{_sbindir}/*
