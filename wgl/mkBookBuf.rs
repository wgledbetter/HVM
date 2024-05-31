use ::hvm::ast;
use clap::{Arg, Command};
use std::fs;

fn main() {
    let cmd_matches = Command::new("mkBookBuf")
        .arg(Arg::new("hvmFile").required(true))
        .arg_required_else_help(true)
        .get_matches();

    let hvm_source_file = cmd_matches.get_one::<String>("hvmFile").expect("required");
    let hvm_code = fs::read_to_string(hvm_source_file).expect("Unable to read file");
    let hvm_book = ast::Book::parse(&hvm_code)
        .unwrap_or_else(|er| panic!("{}", er))
        .build();
    let mut book_buf: Vec<u8> = Vec::new();
    hvm_book.to_buffer(&mut book_buf);
    let bookb = format!("{:?}", book_buf)
        .replace("[", "{")
        .replace("]", "}");
    let bookb = format!("static const u8 BOOK_BUF[] = {};", bookb);

    let buffer_out_file = format!("{}_book.h", hvm_source_file);
    fs::write(buffer_out_file, bookb).expect("Failed to write output.");
}
