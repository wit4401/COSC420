/*
 * This program completes the necessary tasks for the second programming assignment.
 * Various comments on the functionalities of the different functions (Hadoop and Java).
 *
 * See COSC420 repository for more information...
*/
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.ArrayList;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class socialNetwork {
    public static class PairMapper extends Mapper<Object,Text,Text,Text>{
        public void map(Object obj,Text friends,Context context)throws IOException, InterruptedException{
            String[] list = friends.toString().split(" ",0);
            String[] pairs = new String[2];
            for(int i=1;i<list.length;i++){
                for(int j=i+1;j<list.length;j++){
                    String pair = list[i] + list[j];
                    pairs[0] = list[0] + list[i];
                    pairs[1] = list[0] +list[j];
                    String key="";
                    for(int k=1;k<list.length;k++){
                        key+=list[0]+list[k];
                        if(i!=list.length-1)
                            key+=" ";
                    }
                    context.write(new Text(key),new Text(pair + "=" + pairs[0] + " " + pairs[1]));
                }
            }
        }
    }

    public static class TripletReducer extends Reducer<Text,Text,Text,Text>{
        public void reduce(Iterable<Text> keys,Text value,Context context)throws IOException, InterruptedException{
            String[] edges = value.toString().split("=",0);
            String compare = edges[0];
            String userId = edges[1].substring(1,2);
            for (Text edgeList : keys){
                String[] friendList = edgeList.toString().split(" ",0);
                for(int i=0;i<friendList.length;i++){
                    if(compare.equals(friendList[i]))
                        context.write(new Text("<"+userId+","+friendList[0]+","+friendList[i]+">"),new Text(" "));
                }
            }
        }
    }

    public static void main(String[] args)throws Exception{
        Configuration conf = new Configuration();

        Job job1 = Job.getInstance(conf, "social network1");
        job1.setJarByClass(socialNetwork.class);
        job1.setMapperClass(PairMapper.class);
        job1.setReducerClass(TripletReducer.class);
        job1.setOutputKeyClass(Text.class);
        job1.setOutputValueClass(Text.class);
        FileInputFormat.addInputPath(job1, new Path(args[0]));
        FileOutputFormat.setOutputPath(job1, new Path(args[1]));
        
        System.exit(job1.waitForCompletion(true) ? 0 : 1);

    }
}
