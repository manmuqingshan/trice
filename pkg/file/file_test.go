// Copyright 2020 Thomas.Hoehenleitner [at] seerose.net
// Use of this source code is governed by a license that can be found in the LICENSE file.

// blackbox tests
package file_test

import (
	"os"
	"testing"

	"github.com/rokath/trice/pkg/assert"
	"github.com/rokath/trice/pkg/file"
)

func TestReadLines(t *testing.T) {
}

func TestWriteLines(t *testing.T) {
}

func TestSortLines(t *testing.T) {
}

func TestUniqueString(t *testing.T) {
}

func TestUniqueLines(t *testing.T) {
}

func TestRemoveWindowsLineEndings(t *testing.T) {
}

func TestRemoveFromSlice(t *testing.T) {
}

func TestLineNumber(t *testing.T) {
}

var (
	one = "testdata/dir/one.txt"
	two = "testdata/dir/two.txt"
)

func TestCopy(t *testing.T) {
	src := two
	dest := two + ".copied"
	assert.ErrorNil(t, file.Copy(src, dest))
	assert.EqualFiles(t, src, dest)
	assert.ErrorNil(t, os.Remove(dest))
}

func TestCopyDir(t *testing.T) {
	src := "./testdata/dir"
	dest := src + ".copied"
	assert.ErrorNil(t, file.CopyDir(src, dest))
	assert.ErrorNil(t, os.RemoveAll(dest))
}