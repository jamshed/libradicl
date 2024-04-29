# libradicl
Library for writing Reduced Alignment Data (RAD) format files.


# Usage
```

// Throughout, `type` is one of the following:
// null, b, u8, u16, u32, u64, f32, f64, str


// Define header 
RAD::Header header(...)


// Define tags
RAD::Tag_Defn tag_defn

tag_defn.add_file_tag<RAD::Type::type>("tag_name")
...

tag_defn.add_read_tag<RAD::Type::type>("tag-name")
...

tag_defn.add_aln_tag<RAD::Type::type>("tag-name")
...


// Define RAD-writer
RAD::RAD_Writer writer(header, tag_defn, "output-path")

// Define read-record variable
RAD::Single_End_Read read_rec (or, RAD::Paired_End_Read read_rec)

// Define alignment-record variable
RAD::Aln_Record aln_rec


// Add to `writer` as following
for each read r
	read_rec.set(aln-count, read-len)

	read_rec.add_tag(RAD::Type::type(...))
	...


	for each alignment aln
		aln_rec.set(ref-id, aln-type)

		aln_rec.add_tag(RAD::Type::type(...))
		...

		read_rec.add_aln_rec(aln_rec)


	writer.add(reac_rec)


// Close RAD-writer
writer.close()

```
